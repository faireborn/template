# My Template

## NLP

```bash
git clone https://github.com/faireborn/template.git
cd template
cd nlp
mkdir build && cd build
cmake ..
make -j $(nproc)
make test
```

## Algorithm

```bash
git clone https://github.com/faireborn/template.git
cd template
cd algorithm
mkdir build && cd build
cmake ..
make -j $(nproc)
make test
```

## Darts

```bash
git clone https://github.com/faireborn/template.git
cd template
cd darts
zig build build -- data/dic.txt
zig build common_prefix_search -- dictionary.data
```
