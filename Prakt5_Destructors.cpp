#include <iostream>
#include <cassert>
#include <windows.h>

class Massiv
{
private:
    int* m_array;
    int m_length;

public:
    Massiv(int length)
    {
        assert(length > 0);
        m_array = new int[length];
        m_length = length;
    }

    // Копіювальний конструктор
    Massiv(const Massiv& other)
    {
        m_length = other.m_length;
		m_array = new int[m_length]; // Тут виділяємо пам'ять для нового масиву
        for (int i = 0; i < m_length; ++i)
            m_array[i] = other.m_array[i];
    }

    // Оператор копіювального присвоєння з перевіркою на самоприсвоєння
    Massiv& operator=(const Massiv& other)
    {
        if (this == &other) // захист від самоприсвоєння
            return *this;

        delete[] m_array; // звільняємо старий масив

        m_length = other.m_length;
        m_array = new int[m_length];
        for (int i = 0; i < m_length; ++i)
            m_array[i] = other.m_array[i];

        return *this;
    }

    ~Massiv()
    {
        delete[] m_array;
    }

    void setValue(int index, int value) { m_array[index] = value; }
    int getValue(int index) const { return m_array[index]; }
    int getLength() const { return m_length; }

    void resize(int newLength)
    {
        if (newLength <= 0)
            return;

        int* newArray = new int[newLength];
        int elementsToCopy = (newLength < m_length) ? newLength : m_length;

        for (int i = 0; i < elementsToCopy; ++i)
            newArray[i] = m_array[i];

        delete[] m_array;
        m_array = newArray;
        m_length = newLength;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Massiv arr1(5);
    for (int i = 0; i < arr1.getLength(); ++i)
        arr1.setValue(i, i + 1);

    Massiv arr2 = arr1; // копіювання

    arr2.resize(10); // зміна розміру

    arr1 = arr2; // присвоєння (копіювання)

    std::cout << "Вміст arr1 після присвоєння:\n";
    for (int i = 0; i < arr1.getLength(); ++i)
        std::cout << arr1.getValue(i) << " ";

    std::cout << "\nВміст arr2:\n";
    for (int i = 0; i < arr2.getLength(); ++i)
        std::cout << arr2.getValue(i) << " ";

    return 0;
}
