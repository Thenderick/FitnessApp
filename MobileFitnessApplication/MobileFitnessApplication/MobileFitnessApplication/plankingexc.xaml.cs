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
    public partial class plankingexc : ContentPage
    {
        static int id = 2;
        public static DatabaseManager db = new DatabaseManager();
        public ObservableCollection<Results> results = db.GetResults(id);
        public ObservableCollection<Results> Results
        {
            get { return results; }
            set { results = value; }
        }
        public plankingexc()
        {
            InitializeComponent();
            abc.ItemsSource = null;
            abc.ItemsSource = results;
            this.BindingContext = this;
            var navigationPage = App.Current.MainPage as NavigationPage;
            navigationPage.BarBackgroundColor = Color.FromHex("#313131");
        }

        public void Startexc(object sender, EventArgs e)
        {
            Navigation.PushAsync(new stop(id, db));
        }
    }
}