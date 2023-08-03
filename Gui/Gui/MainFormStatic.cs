namespace Gui
{
    public class MainFormStatic
    {
        public readonly struct AnalysisWork
        {
            public const string Polyfit = "Polyfit";
            public const string FFT = "FFT";
            public const string FFTPeaks = "FFT peaks";
            public const string FFTPeaksMigration = "FFT peaks migration";

        }

        private static readonly Dictionary<Color, bool> colors = new List<Color>() {
            Color.Blue, Color.Orange, Color.Red, Color.Purple, Color.Green,
            Color.Salmon, Color.DeepSkyBlue, Color.DarkGoldenrod, Color.Brown, Color.Black,
            Color.Tomato, Color.LightGreen, Color.LemonChiffon, Color.GreenYellow, Color.LightGray
        }.ToDictionary(x => x, x => false);

        public static Color GiveAGoodColor()
        {
            List<Color> cls = colors.Where(x => !x.Value).Select(x => x.Key).ToList();
            Color c = cls[new Random().Next(cls.Count)];
            colors[c] = true;
            return c;
        }

        public static void ReleaseAGoodColor(Color? color = null)
        {
            if (color == null)
                colors.Where(x => x.Value).ToList().ForEach(x => ReleaseAGoodColor(x.Key));
            else
                colors[color.Value] = false;
        }
    }
}
