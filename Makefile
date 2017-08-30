CC     := gcc
FLAGS  := `pkg-config --libs sqlite3`
SHARED := -fPIC -shared

REPS   := 1000

all: native-c hybrid.so

native-c: native-c.c
	$(CC) -o native-c native-c.c $(FLAGS)

hybrid.so: hybrid.c
	$(CC) -o hybrid.so hybrid.c $(FLAGS) $(SHARED)

test-table:
	@echo "Program         | Time     "
	@echo "----------------|----------"

test-native-c: native-c
	@rm -f native-c.db
	@printf "Native C        |\n"
	@printf " ⮑  insert      |"
	@time --format=" (%E)" ./native-c $(REPS) 0
	@printf " ⮑  select      |"
	@time --format=" (%E)" ./native-c $(REPS) 1
	@rm -f native-c.db
	@printf " ⮑  both        |"
	@time --format=" (%E)" ./native-c $(REPS) 2

test-native-py:
	@rm -f native-py.db
	@echo "----------------|----------"
	@printf "Native Python   |\n"
	@printf " ⮑  insert      |"
	@time --format=" (%E)" ./native-py.py $(REPS) 0
	@printf " ⮑  select      |"
	@time --format=" (%E)" ./native-py.py $(REPS) 1
	@rm -f native-py.db
	@printf " ⮑  both        |"
	@time --format=" (%E)" ./native-py.py $(REPS) 2

test-hybrid:
	@rm -f hybrid.db
	@echo "----------------|----------"
	@printf "Hybrid C/Python |\n"
	@printf " ⮑  insert      |"
	@time --format=" (%E)" ./hybrid.py $(REPS) 0
	@printf " ⮑  select      |"
	@time --format=" (%E)" ./hybrid.py $(REPS) 1
	@rm -f hybrid.db
	@printf " ⮑  both        |"
	@time --format=" (%E)" ./hybrid.py $(REPS) 2

test: all test-table test-native-c test-native-py test-hybrid

clean:
	rm -f *.db native-c hybrid.so
