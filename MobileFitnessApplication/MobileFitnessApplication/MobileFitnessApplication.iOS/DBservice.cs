
using Foundation;
using SQLite;
using System;
using System.IO;
using MobileFitnessApplication.iOS;


[assembly: Xamarin.Forms.Dependency(typeof(DatabaseService))]
namespace MobileFitnessApplication.iOS
{
    public class DatabaseService : IDBinterface
    {
        public SQLiteConnection CreateConnection()
        {
            var sqliteFilename = "iot.db";

            string docFolder = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
            string libFolder = Path.Combine(docFolder, "..", "Library", "Databases");

            if (!Directory.Exists(libFolder))
            {
                Directory.CreateDirectory(libFolder);
            }

            string path = Path.Combine(libFolder, sqliteFilename);

            if (!File.Exists(path))
            {
                var existingDb = NSBundle.MainBundle.PathForResource("iot", "db");
                File.Copy(existingDb, path);
            }

            var connection = new SQLiteConnection(path, false);
            return connection;
        }
    }
}