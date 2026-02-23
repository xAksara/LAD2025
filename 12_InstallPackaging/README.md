# Дз 12

Взята программа с 11 дз

```bash
autoreconf -fisv
./configure --enable-gcov
make
sudo make install
LD_LIBRARY_PATH=/usr/local/lib/ guesser
```

```bash
make gcov #покрытие
make check #тесты
make http #сервер с документацией
```

man лежит в doxygen-doc/man/man1/
