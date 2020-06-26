
using SQLite;
using System.IO;
using MobileFitnessApplication.Droid;





[assembly: Xamarin.Forms.Dependency(typeof(DatabaseService))]
namespace MobileFitnessApplication.Droid
{
    public class DatabaseService : IDBinterface
    {
        public SQLiteConnection CreateConnection()
        {
            string sqliteFilename = "iot.db";

            string docdirpath = System.Environment.GetFolderPath(System.Environment.SpecialFolder.Personal);
            var path = Path.Combine(docdirpath, sqliteFilename);

            if (!File.Exists(path))
            {
                using (var binaryReader = new BinaryReader(Android.App.Application.Context.Assets.Open(sqliteFilename)))
                {
                    using (var binaryWriter = new BinaryWriter(new FileStream(path, FileMode.Create)))
                    {
                        byte[] buffer = new byte[2048];
                        int length = 0;
                        while ((length = binaryReader.Read(buffer, 0, buffer.Length)) > 0)
                        {
                            binaryWriter.Write(buffer, 0, length);
                        }
                    }

                }

            }
            var conn = new SQLiteConnection(path, false);
            return conn;
        }
    }
}