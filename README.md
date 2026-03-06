# EnscriptenTesting
Playing with Enscripten for my C++ students
**Using Chapter 10 Juice Machine Version 2 as an Example**
## How to install Enscripten  
Copy/Paste the following into terminal:  
```
# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git

# Enter that directory
cd emsdk
```

Then, check for updates by Copy/Pasting the following into terminal:   
```
# Fetch the latest version of the emsdk (not needed the first time you clone)
git pull

# Download and install the latest SDK tools.
./emsdk install latest

# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest

# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh
```

It may take a minute or two to unpack, so be patient with it.  
Then, you need to change back to your original directory.  
The easiest way to do this is to right click on `main.cpp` and select copy path.

Into the terminal, enter the following:
```
cd  
# Add your own relative path minus /main.cpp at the end.
cd /workspaces/EnscriptenTesting
```

Now you can compile using the following code:
```
em++ *.cpp -o index.html
```

To make sure your website deploys, copy the .gitignore file here and add it to your repo.  
Then you can commit and deploy with GitHub Pages.  
(You can come back and delete the entire emsdk folder when you are happy with your project.)

em++ main.cpp -o program.js -sASYNCIFY -sFORCE_FILESYSTEM