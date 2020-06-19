using SQLite;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using Xamarin.Forms;



namespace MobileFitnessApplication
{
    public class DatabaseManager : ContentPage
    {
        public SQLiteConnection Db { get; set; }



        public DatabaseManager()
        {
            Db = DependencyService.Get<IDBinterface>().CreateConnection();


        }

        public ObservableCollection<Results> GetResults()
        {
            ObservableCollection<Results> f;
            List<Results> lis = Db.Query<Results>("select * from Results");
            f = new ObservableCollection<Results>(lis);

            return f;


        }

        public List<User> Getuser(string usename, string pssword)
        {
           
            
           List<User> m =  Db.Query<User>($"select * from User where Username='{usename}' and Password='{pssword}'");
           return m;
           
          
           




        }

        public void Register(string username, string password)
        {
            Db.Insert(
            new User
            {

                Username = username,
                Password = password

            }
            );
        }

        public void newresult(int userid, double time, int oefId, int Reps = 0)
        {
            Db.Insert(
            new Results
            {
                UserId = userid,
                tijd = time,
                oefeningid = oefId,
                reps = Reps


            }
            );
        }


        public void DeleteUser(string username)
        {
            Db.Query<User>($"delete from User Username ='{username}'");

        }

        public void DeleteResult(int resultid)
        {
            Db.Query<Results>($"delete from Results where resultid='{resultid}'");
        }











    }
}


