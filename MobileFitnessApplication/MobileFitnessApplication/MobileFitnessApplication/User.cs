using System;
using System.Collections.Generic;
using System.Text;
using SQLite;


namespace MobileFitnessApplication
{
    [Table("User")]
    public class User
    {
        [PrimaryKey, AutoIncrement, Unique, NotNull]
        public int UserId { set; get; }

        [Unique, NotNull]
        public string Username { set; get; }
        [NotNull]
        public string Password { set; get; }

        public double weight { set; get; }

        public int leglength { set; get; }

    }
}
