using SQLite;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using Xamarin.Forms;



namespace MobileFitnessApplication
{
    public class DatabaseManager : ContentPage
    {
        private SQLiteConnection Db;

        /// <summary>
        /// makes a new connection to the DB
        /// </summary>
        public DatabaseManager()
        {
            Db = DependencyService.Get<IDBinterface>().CreateConnection();


        }

        /// <summary>
        /// gets all results objects from database
        /// </summary>
        /// <returns>An observablecollection with all results</returns>
        public ObservableCollection<Results> GetResults(int id)
        {
            string a = id.ToString();
            ObservableCollection<Results> f;
            List<Results> lis = Db.Query<Results>($"select * from Results where oefeningid ={a}");
            f = new ObservableCollection<Results>(lis);
            return f;
        }

       
        
        /// <summary>
        /// adds a new result into the ddatabase
        /// </summary>
        /// <param name="oefId"></param>
        /// <param name="Reps"></param>
        /// <param name="time"></param>
        public void newresult(int oefId, int Reps = 0, double time = 0)
        {
            Db.Insert(
            new Results
            {
                tijd = time,
                oefeningid = oefId,
                reps = Reps
            }
            );
        }
    }
}


