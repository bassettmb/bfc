#bfc

bfc is an optimizing brainfuck compiler targeting C.

## Dependencies

A C++14 compiler such as Clang 3.5 or GCC 5.0.

## Installation

mkdir $BUILD\_DIR
cd $BUILD\_DIR
cmake -DCMAKE\_INSTALL\_PREFIX:PATH=$PREFIX ../path/to/bfc/source
make && make install (or other platform-specific build tool)

## Use

bfc programs can be run as standalone programs when linked against bfcentry
or called into manually from C. The following shows how to build a
standalone program:

bfc $SOURCE\_FILE
cc $SOURCE\_FILE.c -lbfcentry -lbfcrts

When calling into brainfuck from C, the bfc runtime must first be
initialized via `void bfc_init(FILE *input, FILE *output)` and then the
`void bfc_main(void)` entry point may be used to start brainfuck execution.

## Team Members
- AJ Ballway
- Connor McGowan
- Michael Bassett

## Development Guidelines
- All code in the master branch must functional and fully tested
- Each feature must be on its own branch
- All finished features should be pushed into a develop branch
- The develop branch should be pushed into master for each major version update
- Master will not be pushed to except for version releases and hotfixes
- Use good code style
- All features should have full test coverage
- Features should be added in the order of user story priority
- All parts of the code should be documented (defining functionality, inputs, and outputs)
- Code should be fully commented

## User Stories

### Submitted by Team

#### High Priority
1. As a project manager, I want to be able to port a brainfuck codebase into C
2. As a brainfuck developer, I want the compiler to check for code correctness
3. As a brainfuck developer, I want the compiler to produce useful error messages

#### Medium Priority
1. As a project manager, I want any ported code to be optimized for efficiency
2. As a brainfuck developer, I want an option to automatically compile any generated C code into an executable

#### Low Priority
1. As a project manager, I want to be able to port a brainfuck codebase into multiple languages
2. As a brainfuck developer, I want to be able to choose between different optimization levels when compiling my code
3. As a brainfuck developer, I want the tool to include a REPL to interpret and run brainfuck code on the fly

### Submitted by Class
(We did not receive user stories from the group responsible for creating them.)
