using SQLite;

namespace MobileFitnessApplication
{
    public interface IDBinterface
    {
       SQLiteConnection CreateConnection();
    }
}
