using NAudio.Wave;
using NAudio.Wave.SampleProviders;
using NCalc;
using NAudio.Utils;
using System.Diagnostics.Eventing.Reader;
using Microsoft.VisualBasic;
using ScottPlot;
using System.Threading.Channels;

namespace ArbitraryWaveformGenerator
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
            AddDefaultComponentValue();
            dataGridViewComponents.RowsAdded += DataGridViewComponents_RowsAdded;
            dataGridViewComponents.CellValidated += DataGridViewComponents_EditingControlShowing;
            splitContainer1.SplitterDistance = splitContainer1.Width / 2;
            splitContainer2.SplitterDistance = splitContainer2.Width / 2;
        }

        private void AddDefaultComponentValue()
        {
            DataGridViewRow lastRow = dataGridViewComponents.Rows.Cast<DataGridViewRow>().Last();

            DataGridViewCheckBoxCell enabled = (DataGridViewCheckBoxCell)(lastRow.Cells[0]);
            enabled.Value = true;

            DataGridViewTextBoxCell gain = (DataGridViewTextBoxCell)(lastRow.Cells[2]);
            gain.Value = UInt16.MaxValue;

            DataGridViewComboBoxCell types = (DataGridViewComboBoxCell)(lastRow.Cells[3]);
            types.Items.AddRange(Enum.GetValues<SignalGeneratorType>().Select(x => x.ToString()).ToArray());
            types.Value = SignalGeneratorType.Sin.ToString();

            DataGridViewComboBoxCell transform = (DataGridViewComboBoxCell)(lastRow.Cells[4]);
            transform.Items.AddRange(new string[]
            {
                "t",
                "1/t",
                "1/Pow(t, 2)",
                "Sqrt(t)",
                "Abs(t)",
                "Pow(t, 2)",
                "Log(t, 2)",
                "Log(Abs(t), 2)",
            });
            transform.Value = transform.Items[0];
        }

        private void DataGridViewComponents_RowsAdded(object? sender, DataGridViewRowsAddedEventArgs e)
        {
            AddDefaultComponentValue();
        }

        private void DataGridViewComponents_EditingControlShowing(object? sender, DataGridViewCellEventArgs e)
        {
            List<Tuple<object, object, object, object>> table = dataGridViewComponents.Rows.Cast<DataGridViewRow>().Where(x => (bool)(x.Cells[0].Value ?? false)).Select(x => Tuple.Create(x.Cells[1].Value, x.Cells[2].Value, x.Cells[3].Value, x.Cells[4].Value)).ToList();
            List<Tuple<double, double, SignalGeneratorType, Expression>> components = table
                .Where(x => double.TryParse(x.Item1?.ToString(), out double tmp1) && double.TryParse(x.Item2?.ToString(), out double tmp2) && Enum.TryParse(x.Item3?.ToString(), out SignalGeneratorType tmp3) && !new Expression(x.Item4.ToString()).HasErrors())
                .Select(x => Tuple.Create(double.Parse(x.Item1.ToString() ?? "0"), double.Parse(x.Item2.ToString() ?? "0"), (SignalGeneratorType)Enum.Parse(typeof(SignalGeneratorType), x.Item3.ToString() ?? SignalGeneratorType.Sin.ToString()), new Expression(x.Item4.ToString())))
                .ToList();

            if (components.Count == 0)
                return;

            //Compute the waveform
            const int sampleRate = 192000;
            const int channels = 2;
            WaveFormat waveFormat = WaveFormat.CreateIeeeFloatWaveFormat(sampleRate, channels);
            double minFrequency = components.Min(x => x.Item1);
            int points = (int)(waveFormat.SampleRate / minFrequency); //number of points to create a waveform

            Dictionary<double, double> signal = Enumerable.Range(0, points).ToDictionary(x => (double)x, x => 0.0);
            for (int i = 0; i < components.Count; i++)
            {
                double frequency = components[i].Item1;
                double amplitude = components[i].Item2;
                SignalGeneratorType type = components[i].Item3;
                Expression expr = components[i].Item4;

                Dictionary<double, double> component = Enumerable.Range(0, points).ToDictionary(x => (double)x, x => 0.0);
                if (frequency == 0)
                    component = Enumerable.Range(0, points).ToDictionary(x => (double)x, x => amplitude);
                else
                {
                    switch (type)
                    {
                        case SignalGeneratorType.Sin:
                            component = component.ToDictionary(x => x.Key, x => amplitude * Math.Sin(2 * Math.PI / points * x.Key * frequency / minFrequency));
                            break;
                        case SignalGeneratorType.Square:
                            MessageBox.Show("Not implemented");
                            break;
                        case SignalGeneratorType.Triangle:
                            MessageBox.Show("Not implemented");
                            break;
                        case SignalGeneratorType.White:
                            component = component.ToDictionary(x => x.Key, x => amplitude * (new Random().NextDouble() * 2.0 - 1.0) / 2);
                            break;
                        default:
                            MessageBox.Show("Not implemented");
                            break;
                    }

                    component = component.ToDictionary(x => x.Key, x =>
                    {
                        expr.Parameters["t"] = x.Value;
                        return (double)Convert.ChangeType(expr.Evaluate(), typeof(double));
                    });
                }

                signal = signal.ToDictionary(x => x.Key, x => x.Value + component[x.Key]);
            }

            //Remove infinities
            signal = signal.Where(x => double.IsFinite(x.Value)).ToDictionary(x => x.Key, x => x.Value);

            //Draw plot
            formsPlot.Plot.Clear();
            formsPlot.Plot.AddSignalXY(signal.Keys.ToArray(), signal.Values.ToArray());
            formsPlot.Refresh();

            //Create wavefile
            string tempFile = Path.Combine(Path.GetTempPath(), Guid.NewGuid().ToString() + ".wav");
            WaveFileWriter waveFileWriter = new(tempFile, waveFormat);

            float[] samples = signal.Values.Select(x => (float)Convert.ChangeType(x, typeof(float))).ToArray();
            if (!samples.ToList().TrueForAll(x => float.IsFinite(x)))
                return;

            //Normalize
            float max = samples.Max();
            samples = samples.Select(x => x / max).ToArray();

            const int duration = 5;
            int repete = (int)minFrequency * duration;
            repete = repete == 0 ? 1 : repete;
            samples = Enumerable.Repeat(samples, repete).SelectMany(x => x).ToArray();

            waveFileWriter.WriteSamples(samples, 0, samples.Length);
            waveFileWriter.Close();
            waveFileWriter.Dispose();

            GC.Collect();

            WaveFileReader reader = new(tempFile);
            WaveOut waveOut = new(); // or WaveOutEvent()
            waveOut.Init(reader);
            waveOut.Play();

            ////Apply function transform
            //string function = textBoxCustomFunction.Text;
            //if (string.IsNullOrEmpty(function))
            //    function = comboBoxStandardFunctions.Text;
            //if (!string.IsNullOrEmpty(function))
            //{
            //    Expression expr = new(function);
            //    xy = xy.ToDictionary(x => x.Key, x =>
            //    {
            //        expr.Parameters["t"] = x.Value;
            //        return (double)Convert.ChangeType(expr.Evaluate(), typeof(double));
            //    }).Where(x => double.IsFinite(x.Value)).ToDictionary(x => x.Key, x => x.Value);
            //}

            //Create wavefile
            //WaveFormat waveFormat = WaveFormat.CreateIeeeFloatWaveFormat(44100, 2);
            //if (!expression && false)
            //{
            //    List<ISampleProvider> samples = new();
            //    for (int i = 0; i < components.Count; i++)
            //    {
            //        double frequency = components[i].Item1;
            //        double amplitude = components[i].Item2;
            //        SignalGeneratorType type = components[i].Item3;
            //        SignalGenerator sg = new() { Frequency = frequency, Gain = amplitude, Type = type };

            //        if (!sg.WaveFormat.Equals(waveFormat))
            //            throw new FormatException("WaveFormat is different from expected");

            //        samples.Add(sg.Take(new TimeSpan(1, 0, 0)));
            //    }
            //}
            //else
            //{

            //}

            //new Thread(new ThreadStart(() =>
            //{
            //    MixingSampleProvider mixer = new(samples);
            //    WaveFileWriter.CreateWaveFile16("mixed.wav", mixer);
            //}))
            //{ IsBackground = true }.Start();
            //}
        }
    }
}