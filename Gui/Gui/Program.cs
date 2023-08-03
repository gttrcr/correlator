using Common;
using System.Diagnostics;
using System.Reflection;
using System.Windows.Forms;

namespace Gui
{
    internal static class Program
    {
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            Application.SetHighDpiMode(HighDpiMode.SystemAware);

            UpdateChecker.Get().RepoName = "correlator";
            UpdateChecker.Get().Assembly = Assembly.GetExecutingAssembly();
            UpdateChecker.Get().UpdateCheckCallback += (Version localVersion, Version remoteVersion, Uri downloadLink) =>
            {
                Form form = new();
                form.Size = new(600, 400);
                form.StartPosition = FormStartPosition.CenterScreen;
                form.Text = "Update";
                form.Controls.Clear();
                
                CheckBox hideCheckBox = new();
                hideCheckBox.Text = "Hide";
                hideCheckBox.CheckStateChanged += (object? sender, EventArgs e) => { UpdateChecker.Get().Hide = hideCheckBox.Checked; };
                hideCheckBox.Dock = DockStyle.Bottom;
                form.Controls.Add(hideCheckBox);
                
                Label labelUpdate = new Label();
                labelUpdate.Text = "Update available!";
                labelUpdate.Font = new(labelUpdate.Font.FontFamily, 15, FontStyle.Bold);
                labelUpdate.Size = new(400, 50);
                labelUpdate.TextAlign = ContentAlignment.MiddleCenter;
                labelUpdate.Dock = DockStyle.Top;

                List<string> lines = new List<string>{
                    Environment.NewLine,
                    "There is an update available for this application",
                    Environment.NewLine,
                    "Your local version is: " + localVersion.ToString(),
                    Environment.NewLine,
                    "Your remove version is: " + remoteVersion.ToString(),Environment.NewLine,
                    "Download the update at the following link",
                    downloadLink.ToString() };
                lines.Reverse();

                form.Controls.AddRange(lines.Select(x =>
                {
                    UriKind uriKind = new();
                    if (!Uri.IsWellFormedUriString(x, uriKind))
                        return new Label()
                        {
                            Text = x,
                            Dock = DockStyle.Top
                        };
                    else
                    {
                        LinkLabel label = new()
                        {
                            Text = x,
                            Dock = DockStyle.Top
                        };
                        label.LinkClicked += (object sender, LinkLabelLinkClickedEventArgs e) =>
                        {
                            label.LinkVisited = true;
                            Process.Start("explorer", label.Text);
                        };

                        return label;
                    }
                }).ToArray());
                form.Controls.Add(labelUpdate);

                form.ShowDialog();
            };

            Application.Run(new MainForm());
        }
    }
}