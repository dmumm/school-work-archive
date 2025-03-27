

using namespace std;

class NumberCount {
  public:
    // constructors
    NumberCount(int mi, int ma) : min(mi), max(ma)
    {
      data = new int[max - min + 1];
      fill(data, data + sizeof(data), 0);
    }

    NumberCount() : min(0), max(0)
    {
      data = new int[9]);
      fill(data, data + sizeof(data), 0);
    }

    // mutators
    void addElement(int number)
    {
      if(number >= min && number <= max) {
        date[number-min]++;
      }
      else {
        cout << number << " out of range;" << endl;
      }
    }

    bool removeNumber(int number)
    {
      if(date[number-min] > 0 && number >= min && number <= max) {
        date[number-min]--;
        return true;
      }

      else if(number < min && number > max) {
        cout << number << " out of range;" << endl;
        return false;
      }

      else {
        cout << number << " not present;" << endl;
      }

    }

    void display()
    {
      for(int i = 0; i < max-min; i++) {
        cout << i+min << ": ";
        for(int j = 0; j < data[i]; i++) {
          cout << "*";
        }
        cout << endl;
      }
    }

  private:
    int min;
    int max;
    int* data;
};

int main(){

  NumberCount N(11,16);
  N.addElement(12);
  N.addElement(12);
  N.addElement(12);
  N.addElement(14);
  N.addElement(17);
  N.addElement(13);
  N.removeElement(11);
  N.removeElement(13);
  N.display();


  return 0;
}
