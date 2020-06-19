using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace MobileFitnessApplication
{
    [XamlCompilation(XamlCompilationOptions.Compile)]
    public partial class register : ContentPage
    {
        DatabaseManager b;
        public register(DatabaseManager a)
        {
            InitializeComponent();
            b = a;
        }

        private void btn3_Clicked(object sender, EventArgs e)
        {
            b.Register(username.Text, password.Text);
        }
    }
}