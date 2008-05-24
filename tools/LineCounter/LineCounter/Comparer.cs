using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Windows.Forms;

namespace LineCounter
{
    class ListViewItemComparer : IComparer
    {
        public int Column
        {
            get;
            set;
        }

        public bool Numeric
        {
            get;
            set;
        }

        public bool Descending
        {
            get;
            set;
        }

        public ListViewItemComparer(int column)
        {
            Column = column;
        }

        public int Compare(object x, object y)
        {
            ListViewItem listX;
            ListViewItem listY;

            if (Descending)
            {
                listY = x as ListViewItem;
                listX = y as ListViewItem;
            }
            else
            {
                listX = x as ListViewItem;
                listY = y as ListViewItem;
            }

            if (Numeric)
            {
                decimal valX, valY;
                decimal.TryParse(listX.SubItems[Column].Text, out valX);
                decimal.TryParse(listY.SubItems[Column].Text, out valY);

                return decimal.Compare(valX, valY);
            }
            else
            {
                return string.Compare(listX.SubItems[Column].Text, listY.SubItems[Column].Text);
            }
        }
    }
}
