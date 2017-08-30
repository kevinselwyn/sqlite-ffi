# sqlite-ffi

Experiments in Python FFI with Sqlite

## Requirements

Works best on Linux:

```text
sudo apt-get install libsqlite3-dev
```

Or use [Vagrant](https://www.vagrantup.com/):

```text
vagrant up && vagrant ssh
```

## Usage

```text
make test
```

To specify reps (number of inserts/select):

```text
make test REPS=10000
```

## Output

```text
Program         | Time
----------------|----------
Native C        |
 ⮑  insert     | (0:00.17)
 ⮑  select     | (0:03.53)
 ⮑  both       | (0:03.29)
----------------|----------
Native Python   |
 ⮑  insert     | (0:00.17)
 ⮑  select     | (0:03.32)
 ⮑  both       | (0:03.59)
----------------|----------
Hybrid C/Python |
 ⮑  insert     | (0:00.18)
 ⮑  select     | (0:03.69)
 ⮑  both       | (0:03.39)
```

## Explanation

Three programs are included:

* Native C program utilizing `libsqlite3`
* Native Python program utilizing the `sqlite3` module
* Hybrid C/Python program that calls a native shared library written in C (an utilizing `libsqlite3`) from Python

The results usually show that Native C is the fastest overall, followed by Hybrid C/Python, and trailing with Native Python.
