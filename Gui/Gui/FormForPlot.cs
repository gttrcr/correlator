using ScottPlot;

namespace Gui
{
    public class FormForPlot : Form
    {
        public FormsPlot Plot { get; set; }
        
        public FormForPlot()
        {
            Plot = new() { Dock = DockStyle.Fill };
            Controls.Add(Plot);
            StartPosition = FormStartPosition.CenterScreen;
            Size = new Size(800, 500);
            Text = "Plot";
            Show();
        }

        public override void Refresh()
        {
            base.Refresh();
            Plot.Refresh();
        }
    }
}
