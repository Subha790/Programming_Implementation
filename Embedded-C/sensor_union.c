#include <stdio.h>
#include <string.h>

union SensorValue
{
    int integerValue;
    float floatValue;
};

struct Sensor
{
    int id;
    char name[50];
    int type;
    union SensorValue value;
};

void readSensor(struct Sensor *sensor)
{
    printf("Enter Sensor ID : ");
    scanf("%d", &sensor->id);

    printf("Enter Sensor Name : ");
    scanf("%49s", sensor->name);

    printf("Choose Reading Type\n");
    printf("1. Integer\n");
    printf("2. Float\n");
    printf("Choice : ");
    scanf("%d", &sensor->type);

    if (sensor->type == 1)
    {
        printf("Enter Integer Reading : ");
        scanf("%d", &sensor->value.integerValue);
    }
    else if (sensor->type == 2)
    {
        printf("Enter Float Reading : ");
        scanf("%f", &sensor->value.floatValue);
    }
    else
    {
        printf("Invalid choice\n");
        sensor->type = 0;
    }
}

void displaySensor(struct Sensor sensor)
{
    printf("\nSensor Details\n");
    printf("ID : %d\n", sensor.id);
    printf("Name : %s\n", sensor.name);

    if (sensor.type == 1)
    {
        printf("Reading : %d\n", sensor.value.integerValue);
    }
    else if (sensor.type == 2)
    {
        printf("Reading : %.2f\n", sensor.value.floatValue);
    }
}

void updateSensor(union SensorValue *value, int type)
{
    if (type == 1)
    {
        printf("Enter Updated Integer Value : ");
        scanf("%d", &value->integerValue);
    }
    else if (type == 2)
    {
        printf("Enter Updated Float Value : ");
        scanf("%f", &value->floatValue);
    }
}

int compareSensor(struct Sensor s1, struct Sensor s2)
{
    if (s1.type != s2.type)
        return 0;

    if (s1.type == 1)
        return s1.value.integerValue == s2.value.integerValue;

    if (s1.type == 2)
        return s1.value.floatValue == s2.value.floatValue;

    return 0;
}

void resetSensor(union SensorValue *value)
{
    value->integerValue = 0;
}

int main()
{
    struct Sensor sensor1, sensor2;

    readSensor(&sensor1);

    if (sensor1.type == 2)
        printf("\n%s = %.2f\n", sensor1.name, sensor1.value.floatValue);
    else if (sensor1.type == 1)
        printf("\n%s = %d\n", sensor1.name, sensor1.value.integerValue);

    displaySensor(sensor1);

    printf("\nUpdating Reading...\n");
    updateSensor(&sensor1.value, sensor1.type);

    if (sensor1.type == 2)
        printf("Updated Value : %.2f\n", sensor1.value.floatValue);
    else if (sensor1.type == 1)
        printf("Updated Value : %d\n", sensor1.value.integerValue);

    return 0;
}
