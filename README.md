# Simple blackjack game in C

This was my first time using C in over 2 years, and I did not use an LLM assistants for code generation, though ChatGPT did help with the makefile.  
Uses [Unity](https://github.com/ThrowTheSwitch/Unity) for unit tests.  
There is room for future development to clean up the play_game and play_round functions, and making some tests for them, as well as adding different options to players such as doubling down and surrendering.

Build:  
`$ make`

Run:  
`$./blackjack <player count> <deck count>`

Run tests:  
`$ make test`
