using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace MobileFitnessApplication
{
    [XamlCompilation(XamlCompilationOptions.Compile)]
    public partial class stop : ContentPage
    {
        private int id;
        private int c;
        private DatabaseManager db;
        static private string a = "192.168.178.88";//Verander IP naar ip adres van arduino server
        static private int b = 80;
        Client client1 = new Client(a, b);
        public stop(int i, DatabaseManager d)
        {
            id = i;
            db = d;
            string command = "0";
           
            switch (id)
            {
                case 1:
                    command = "p";
                    break;
                case 2:
                    command = "l";
                    break;
                case 3:
                    command = "s";
                    break;
            }

            client1.OpenConnection();
            client1.Send(command);
            InitializeComponent();
            NavigationPage.SetHasNavigationBar(this, false);
        }

        public void stopexc(object sender, EventArgs e)
        {
            string received = client1.Recieve("b");
            c = Convert.ToInt32(received);
            client1.CloseConnection();
            int t;
            int r;
            if (id == 2)
            {
                t = c;
                r = 0;
            }
            else
            {
                r = c;
                t = 0;
            }


            db.newresult(id,r,t);
            Navigation.PopToRootAsync();
            
        }
    }
}