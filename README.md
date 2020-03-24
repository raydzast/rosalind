## О проекте
Репозиторий содержит решения задач по бионформатике с ресурса [rosalind.info](https://rosalind.info/), выполненных в рамках учебной практики 4 семестра.

## Сборка
В файле `CMakeFiles.txt` задается имя задачи для сборки. Имя задается как константа с именем `NAME` в строке [#6](https://github.com/lipoponi/rosalind/blob/master/CMakeLists.txt#L6)

```shell-script
mkdir -p cmake-build
cd cmake-build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug .. && make
```

## Запуск
Перед запуском необходимо поместить входные данные в папку `inputs`. Входной файл к задаче должен называться `%название-задачи%.txt`.

```shell-script
mkdir -p outputs
./cmake-build/run
```
