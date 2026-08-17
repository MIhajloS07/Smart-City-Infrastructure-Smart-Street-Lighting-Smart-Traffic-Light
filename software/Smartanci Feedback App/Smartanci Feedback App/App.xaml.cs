using Microsoft.Extensions.DependencyInjection;
using Smartanci_Feedback_App;

namespace Smartanci_Feedback_App
{
    public partial class App : Application
    {
        public App()
        {
            InitializeComponent();
            MainPage = new MainPage();
        }
    }
}