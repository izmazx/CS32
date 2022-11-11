//
//  main.cpp
//  homework3
//
//  Created by Izma Zuberi on 4/29/22.
//

/*

class Landmark
{
  public:
    Landmark(string s): m_name(s), m_color("yellow")
    {};
    virtual ~Landmark()
    {};
    string name() const
    {return m_name;}
    virtual string color() const
    {return m_color;}
    virtual string icon() const = 0;
  private:
    string m_name;
    string m_color;
};

class Hotel: public Landmark
{
  public:
    Hotel(string s): Landmark(s)
    {}
    ~Hotel()
    {cout << "Destroying the hotel " << name() << "." << endl;}
    virtual string icon() const
    { return ("bed"); }
    
};

class Restaurant: public Landmark
{
  public:
    Restaurant(string s, int i): Landmark(s), m_size(i)
    {}
    ~Restaurant()
    {cout << "Destroying the restaurant " << name() << "." << endl;}
    virtual string icon() const
    {
        if (m_size < 40)
            return ("small knife/fork");
        else
            return("large knife/fork");
    }
  private:
    int m_size;
};

class Hospital: public Landmark
{
  public:
    Hospital(string s): Landmark(s)
    {};
    ~Hospital()
    {cout << "Destroying the hospital " << name() << "." << endl;}
    virtual string color() const
    {return "blue";}
    virtual string icon () const
    {return "H icon";}
};

*/
