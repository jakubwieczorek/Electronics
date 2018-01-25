#include<string>

void menu(bool);//wyswietla menu w main. jako warunek przyjmuje true gdy nie wyswietlam mozliwosci usuwania eksportu itd. a gdy false to
//wyswietla
void str(std::string &, const char*);
void check(short &to_check, const char *str, int n, ...);//n ilosc dodatkowych argumentow, pierwszy dodatkowy to  min drugi max.
// powyższa jest zwykłym analizatorem leksykalnym do poprawnosci wprowadzonych danych, gdy chce ograniczyc dane z gory to 2 argumenty
//dodatkowe a gdy tylko z dolu to 1
void add(short*);//to daje elementy kolorowe
bool choice(const char*);//sprawdza wybory użytkownika tak/nie, argument przyjmuje napis do wyswietlenia na ekranie

