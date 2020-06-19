using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices.ComTypes;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;
using System.Configuration;
using System.Diagnostics;

namespace MobileFitnessApplication
{

    [DesignTimeVisible(false)]
    public partial class MainPage : ContentPage
    {
        public static DatabaseManager a = new DatabaseManager();
        
       
        
        public MainPage()
        {
            InitializeComponent();
            
        }

        private void Button_Clicked(object sender, EventArgs e)
        {
            var d = a.Getuser(username.Text, password.Text);
            if (d.Count != 0)
            {
                Navigation.PushAsync(new register(a));
            }
            else
            {

            }
        }

        private void Button_Clicked_1(object sender, EventArgs e)
        {
            Navigation.PushAsync(new register(a));

        }
    }
}
