using System;
using System.Collections.Generic;
using System.Text;
using SQLite;

namespace MobileFitnessApplication
{
    public class Results
    {
        [PrimaryKey, AutoIncrement, Unique, NotNull]
        public int resultid { get; set; }
        [NotNull]
        public int oefeningid { get; set; }

        public int reps { get; set; }
        [NotNull]
        public double tijd { get; set; }
        [NotNull]
        public int UserId { get; set; }
    }
}
