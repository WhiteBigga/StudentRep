using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Xml.Serialization;
using System.Collections;

namespace FuncTest
{
    class Program
    {
        static Random rnd = new Random();
        static void CreateRobots()
        {
            int N;
            Console.WriteLine("Введите N: ");
            while (!int.TryParse(Console.ReadLine(), out N) || N <= 0)
            {
                Console.WriteLine("Incorrect Input");
            }
            for (int i = 0; i < N; i++)
            {
                try
                {
                    robots.Add(new Robot() { });
                }
                catch (ArgumentException e)
                {
                    Console.WriteLine(e.Message);
                    i--;
                }
            }
        }

        static string GenerateName(int length)
        {
            string res = string.Empty;
            for (int i = 0; i < length; i++)
            {
                if (rnd.Next(0, 2) == 0)
                {
                    res += rnd.Next(33) == 32 ? 'ё' : (char)rnd.Next('а', 'я');
                }
                else
                {
                    res += rnd.Next(33) == 32 ? 'Ё' : (char)rnd.Next('А', 'Я');
                }
            }
            return res;
        }

        // xml serialization
        // [XmlInclude(typeof())]
        static void Serialize()
        {
            using (FileStream fs = new FileStream(@"../../../robots.xml", FileMode.Create))
            {
                XmlSerializer xml = new XmlSerializer(typeof(GameRobots<Creation>));
                xml.Serialize(fs, robots);
            }
        }

        static void Deserialize()
        {
            using (FileStream fs = new FileStream(@"../../../robots.xml", FileMode.Open))
            {
                XmlSerializer xml = new XmlSerializer(typeof(GameRobots<Creation>));
                robots = (GameRobots<Creation>)xml.Deserialize(fs);
            }
        }

        static void FirstLinq()
        {
            Console.WriteLine("Первый запрос: ");
            var linq = from r in robots
                       where r is Robot && (double)(Robot)r >= 0.5
                       orderby (double)(Robot)r ascending
                       select r;
            foreach (var item in linq)
            {
                Console.WriteLine(item);
            }
        }

        static void SecondLinq()
        {
            Console.WriteLine("Второй запрос: ");
            var linq = from r in robots
                       where r is Robot
                       orderby r
                       select r
                       group r by r.DifficultyLevel;
            foreach (var item in linq)
            {
                Console.WriteLine(item.Key);
                foreach (var i in item.OrderBy(r => (double)(Robot)r))
                {
                    Console.WriteLine(i);
                }
            }
        }

        // json
        // using System.Runtime.Serialization.Json;
        static public void SerializeBooks(string path, Bookstore<Product> book)
        {
            DataContractJsonSerializer jsonSerializer = new DataContractJsonSerializer(typeof(Bookstore<Product>));
            try
            {
                using (FileStream fs = new FileStream(path, FileMode.Create, FileAccess.Write))
                {
                    jsonSerializer.WriteObject(fs, book);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка в сериализации" + ex.Message);
            }
        }

        static public Bookstore<Product> DeserializeBooks(string path)
        {
            try
            {
                using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read))
                {
                    DataContractJsonSerializer jsonSerializer = new DataContractJsonSerializer(typeof(Bookstore<Product>));
                    return jsonSerializer.ReadObject(fs) as Bookstore<Product>;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка в сериализации" + ex.Message);
                return null;
            }
        }

               
        static void Main(string[] args)
        {
        }
    }

    // итератор
    public class FiguresCollectionEnumerator<T> : IEnumerator<T> where T : Figure
    {
        List<T> figures;
        int Position = -1;

        public FiguresCollectionEnumerator(List<T> figures)
        {
            this.figures = new List<T>();
            for (int i = 0; i < figures.Count; i++)
            {
                if (figures[i].Weight > 0)
                {
                    this.figures.Add(figures[i]);
                }
            }
        }
        public T Current => figures[Position];

        T IEnumerator<T>.Current => figures[Position];

        public void Dispose()
        { }

        public bool MoveNext()
        {
            if (Position < figures.Count - 1)
            {
                Position++;
                return true;
            }
            else return false;
        }

        public void Reset()
        {
            Position = -1;
        }
    }
}
