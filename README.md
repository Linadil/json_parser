## Json Parser

Программа представляет из себя LL(0)-анализатор языка ```json``` с возможностью поиска содержимого по ключам.

## Инструкция по сборке и запуску программы

**Сборка**:
1. ```git clone https://github.com/Linadil/json_parser.git```

2. ```cd json_parser/json_parser```

3. ```mkdir build```

4. ```cmake -B build```

5. ```cd build```

6. ```make```


**Запуск**:
```
./json_parser -f <filename> -k <key>
```

