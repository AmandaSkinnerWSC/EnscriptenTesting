# Go to your workspace folder
cd /workspaces/EnscriptenTesting

# Clone the Emscripten SDK repo
git clone https://github.com/emscripten-core/emsdk.git

cd emsdk

# Pull latest updates
git pull

# Install the latest SDK version
./emsdk install latest

# Activate it for the current shell/user
./emsdk activate latest

# Set up Terminal
source ./emsdk_env.sh