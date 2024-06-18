#include <iostream>
#include <limits>

class Wlasciciel {
public:
    Wlasciciel(const char* nazwisko) : nazwisko_(nazwisko) {}
    const char* getNazwisko() const { return nazwisko_; }
private:
    const char* nazwisko_;
};

const double WAR_POCZ = 10000.0;
const double WSP_SPARW = 1.0;

class Samochod {
private:
    char rejestracja_[10];
    int stanLicznika_;
    bool dopuszczony_;
    Wlasciciel wlasciciel_;
public:
    static int ostatniNumerRejestracyjny;

    Samochod(const char* xxx, int stanLicznika, bool dopuszczony, const Wlasciciel& wlasciciel)
        : stanLicznika_(stanLicznika), dopuszczony_(dopuszczony), wlasciciel_(wlasciciel) {
        ostatniNumerRejestracyjny++;
        strcpy(rejestracja_, xxx);
        strcat(rejestracja_, "-");
        char temp[5];
        int num = ostatniNumerRejestracyjny;
        temp[0] = (num / 1000) + '0';
        temp[1] = ((num / 100) % 10) + '0';
        temp[2] = ((num / 10) % 10) + '0';
        temp[3] = (num % 10) + '0';
        temp[4] = '\0';
        strcat(rejestracja_, temp);
    }

    const char* getRejestracja() const { return rejestracja_; }
    void setRejestracjaXXX(const char* xxx) {
        strcpy(rejestracja_, xxx);
        strcat(rejestracja_, "-");
        char temp[5];
        int num = ostatniNumerRejestracyjny;
        temp[0] = (num / 1000) + '0';
        temp[1] = ((num / 100) % 10) + '0';
        temp[2] = ((num / 10) % 10) + '0';
        temp[3] = (num % 10) + '0';
        temp[4] = '\0';
        strcat(rejestracja_, temp);
    }
    int getStanLicznika() const { return stanLicznika_; }
    void setStanLicznika(int stanLicznika) {
        if (stanLicznika >= 0) {
            stanLicznika_ = stanLicznika;
        }
    }
    bool getDopuszczony() const { return dopuszczony_; }
    void setDopuszczony(bool dopuszczony) { dopuszczony_ = dopuszczony; }
    const Wlasciciel& getWlasciciel() const { return wlasciciel_; }

    virtual double obliczZasieg() const { return 800.0; }

    operator double() const {
        double wartosc = (WAR_POCZ - 0.1 * stanLicznika_) * (dopuszczony_ ? WSP_SPARW : 0.2);
        return wartosc < 400.0 ? 400.0 : wartosc;
    }

    bool operator==(const Samochod& other) const {
        return strcmp(rejestracja_, other.rejestracja_) == 0 && abs(stanLicznika_ - other.stanLicznika_) < 10;
    }
};

int Samochod::ostatniNumerRejestracyjny = 0;

class SamochodElektryczny : public Samochod {
public:
    SamochodElektryczny(const char* rejestracja, int stanLicznika, bool dopuszczony, const Wlasciciel& wlasciciel, int stanBaterii)
        : Samochod(rejestracja, stanLicznika, dopuszczony, wlasciciel), stanBaterii_(stanBaterii) {
        if (stanBaterii < 0 || stanBaterii > 100) {
            throw std::invalid_argument("Stan baterii musi być w zakresie 0-100%");
        }
    }

    int getStanBaterii() const { return stanBaterii_; }
    void setStanBaterii(int stanBaterii) {
        if (stanBaterii >= 0 && stanBaterii <= 100) {
            stanBaterii_ = stanBaterii;
        }
    }

    double obliczZasieg() const override { return 2.5 * stanBaterii_; }

private:
    int stanBaterii_;
};



int main() {
    // Tworzenie właściciela
    Wlasciciel wlasciciel("Nazwisko");

    // Tworzenie samochodów
    Samochod samochod1("ABC", 1000, true, wlasciciel);
    Samochod samochod2("DEF", 2000, false, wlasciciel);

    // Tworzenie samochodu elektrycznego
    SamochodElektryczny samochodElektryczny("GHI", 3000, true, wlasciciel, 50);

    // Używanie getterów i setterów
    std::cout << "Numer rejestracyjny samochodu 1: " << samochod1.getRejestracja() << std::endl;
    samochod1.setRejestracjaXXX("JKL");
    std::cout << "Numer rejestracyjny samochodu 1 po setRejestracjaXXX: " << samochod1.getRejestracja() << std::endl;
    std::cout << "Przebieg samochodu 1: " << samochod1.getStanLicznika() << std::endl;
    samochod1.setStanLicznika(5000);
    std::cout << "Przebieg samochodu 1 po setStanLicznika: " << samochod1.getStanLicznika() << std::endl;
    std::cout << "Czy samochód 1 ma pozwolenie na jazdę: " << (samochod1.getDopuszczony() ? "tak" : "nie") << std::endl;
    samochod1.setDopuszczony(false);
    std::cout << "Czy samochód 1 ma pozwolenie na jazdę po setDopuszczony: " << (samochod1.getDopuszczony() ? "tak" : "nie") << std::endl;
    std::cout << "Właściciel samochodu 1: " << samochod1.getWlasciciel().getNazwisko() << std::endl;

    std::cout << "Numer rejestracyjny samochodu elektrycznego: " << samochodElektryczny.getRejestracja() << std::endl;
    std::cout << "Przebieg samochodu elektrycznego: " << samochodElektryczny.getStanLicznika() << std::endl;
    std::cout << "Czy samochód elektryczny ma pozwolenie na jazdę: " << (samochodElektryczny.getRejestracja() ? "tak" : "nie") << std::endl;
    std::cout << "Właściciel samochodu elektrycznego: " << samochodElektryczny.getWlasciciel().getNazwisko() << std::endl;
    std::cout << "Poziom baterii samochodu elektrycznego: " << samochodElektryczny.getStanBaterii() << std::endl;

    // Używanie operatora konwersji
    double wartoscSamochodu = samochod1;
    std::cout << "Wartość samochodu 1: " << wartoscSamochodu << std::endl;

    // Używanie operatora równości
    std::cout << "Czy samochód 1 jest równy samochodowi 2? " << (samochod1 == samochod2 ? "tak" : "nie") << std::endl;
    std::cout << "Czy samochód 1 jest równy samochodowi elektrycznemu? " << (samochod1 == samochodElektryczny ? "tak" : "nie") << std::endl;

    return 0;
}