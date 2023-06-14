make clean

cp task.h.txt ../FreeRTOS/include/task.h
cp tasks.c.txt ../FreeRTOS/tasks.c

make

cd ../FreeRTOS/
git reset --hard HEAD

