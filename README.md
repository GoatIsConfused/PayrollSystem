# PayrollSystem
Console based cpp payroll system

Program displays use of data structues, dynamically allocated memory, i/o of files, error handling, etc.

The program itself is intuitive to use just follow the menu prompts. If you decide to prematurely exit the program after it has created the specified amount of structures (line 54), it will cause a memory leak so if you dont want that to happen just make sure that you finish writing the employee information and the files gets saved. This happens because the delete line will run only after getting all of the employee information and the file is saved because the structures are still needed for those tasks.

In the event that the program cannot read the settings file because of given permissions or lack of existance the program can still function. Backup values for the rates are hard-coded in and you can still edit these values and create a new file in the settings option.

Format for save files:
name MON TUE WED THU FRI SAT SUN pay
name MON TUE WED THU FRI SAT SUN pay
...
name MON TUE WED THU FRI SAT SUN pay

Format for the settings file:
standardRate supervisorRate managementRate satMultiplyer sunMultiplyer
