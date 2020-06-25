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
using Xamarin.Forms.Xaml;

namespace MobileFitnessApplication
{

    [DesignTimeVisible(false)]

    
    public partial class MainPage : ContentPage
    {
        public static DatabaseManager db = new DatabaseManager();



        public MainPage()
        {
            InitializeComponent();
            NavigationPage.SetHasNavigationBar(this, false);

        }

        private void planking(object sender, EventArgs e)
        {
            Navigation.PushAsync(new plankingexc());
        }

        private void squats(object sender, EventArgs e)
        {
            Navigation.PushAsync(new squatsexc());
        }

        private void pushups(object sender, EventArgs e)
        {
           Navigation.PushAsync(new pushupsexc());
        }
    }
}
