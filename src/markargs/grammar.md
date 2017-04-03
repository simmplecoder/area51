# Grammar

## Variable creation 

Declaration of variable happens when a name is encountered on a new line, without any leading assignment
 (see blow). Variable name can consist of any alphanumeric characters, and underscore (`_`), though
 *it must* start with alphabetic character or underscore.
 
 **Examples:**
 
    Framework
    Flags
    SourceFiles

## Comments

Comments are ignored by the parser. They should consist of number sign (`#`) on a newline (whitespaces may lead),
and any text one desires. The number sign will have its effect until next line.

## Variable manipulation

Variable manipulation happens through applying operators on declared variables. Currently, it supports
 only assigning a value, or an array of values.
 
 ###Value

 A value is a sequence of any visible non whitespace characters. Separation occurs on any whitespace.
 
 ### Assigning single value
 
 Assigning a value happens when a **Variable** is standing on the left hand side of operator equals (`=`),
 and a **Value** is standing on the right hand side of the operator equals.
 
 **Examples:**
 
    CoreCount = 1
    Framework = benchmark_v2
    RunSequence = Serial
    
 ### Assigning an array of values
 
 Assigning an array of values happens when a **Variable** is standing on the left hand side of 
 operator equals (`=`), followed by opening square brace (leading whitespaces allowed), followed by
 any number of **Value**s, each of which end with comma character (`,`). Ending sequence of values
 happens through putting closing square bracket (`]`).

