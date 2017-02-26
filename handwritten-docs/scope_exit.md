#scope_exit

##Specification:

Executes code in curly braces at the end of the current scope. The code inside
of curly can be written as if it is a lambda that captures everything by reference,
e.g. 

    [&]()
    {
        /*code here*/
    }
    
The mechanism itself is based on RAII. So, basically the code is called inside
of the destructor, so if it throws and there is another exception in flight,
runtime will call `std::terminate()`.
    
As noted by standard, the types of the captured variables doesn't change. In fact,
no new variables are even introduced.

##Examples:

    void foo()
    {
        scope_exit 
        {
            logfile << "Leaving foo at " << std::chrono::high_resolution_clock::now();
        };
        /*...*/  
    }
    
Do note that putting `;` is needed both at the last expression and after 
the closing curly brackets `}`.