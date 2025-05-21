#include <stdio.h>
#include <string.h>
#include <math.h>

typedef double (*op_func)(double, double, int *);

typedef struct
{
   char *op;
   op_func func;
} operation;

double add(double a, double b, int *valid) { return a + b; };
double subtract(double a, double b, int *valid) { return a - b; };
double multiply(double a, double b, int *valid) { return a * b; };

double divide(double a, double b, int *valid)
{
   if (b == 0)
   {
      printf("Error: Cannot divide by zero.\n");
      *valid = 0;
      return 1;
   }
   return a / b;
}

double floor_divide(double a, double b, int *valid)
{
   if (b == 0)
   {
      printf("Error: Cannot perform floor division by zero.\n");
      *valid = 0;
      return 2;
   }
   return floor(a / b);
}

double modulus(double a, double b, int *valid)
{
   if (b == 0)
   {
      printf("Error: Cannot find modulus with zero division.\n");
      *valid = 0;
      return 3;
   }
   return fmod(a, b);
}

double power(double a, double b, int *valid)
{
   return pow(a, b);
}

double calculate(double a, char *op, double b, int *valid)
{
   operation ops[] = {
       {"+", add},
       {"-", subtract},
       {"*", multiply},
       {"/", divide},
       {"//", floor_divide},
       {"%", modulus},
       {"**", power},
   };

   size_t ops_count = sizeof(ops) / sizeof(*ops);
   for (size_t i = 0; i < ops_count; i++)
   {
      if (strcmp(op, ops[i].op) == 0)
      {
         return ops[i].func(a, b, valid);
      }
   }

   printf("Error: Unsupported operator.\n");
   *valid = 0;
   return 0;
}

int main()
{

   char expression[100];
   double num1, num2;
   char operator[3];

   while (1)
   {
      printf("Enter a mth expression in the format A <OP> B (or press Enter to quit): ");
      if (!fgets(expression, sizeof(expression), stdin))
      {
         puts("\n");
         break;
      }
      if (expression[0] == '\n')
      {
         break;
      }

      if (sscanf(expression, "%lf %2s %lf", &num1, operator, &num2) != 3)
      {
         printf("Error: Invalid format. User 'A <OP> B'.\n");
         continue;
      }

      int valid = 1;
      double result = calculate(num1, operator, num2, &valid);
      if (valid)
      {
         printf("Result: %g\n", result);
      }
   }

   return 0;
}