
if [ ! -e "depot_tools" ]; then
	echo "Google depot_tools not found, cloning those first"
	git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
fi

export PATH="$(pwd)/depot_tools:$PATH"

mkdir -p v8
cd v8
if [ ! -e "v8" ]; then
	echo "V8 repo not found, cloning new..."
	fetch v8
fi
cd v8

gclient sync
./build/install-build-deps.sh

echo "Seting up build..."

python tools/dev/v8gen.py x64.release
python tools/dev/v8gen.py x64.debug

cp ../../args.release.template ./out.gn/x64.release/args.gn
cp ../../args.debug.template ./out.gn/x64.debug/args.gn

gn gen ./out.gn/x64.release
gn gen ./out.gn/x64.debug

echo "Build files have been generated, ready to build. This might take a long time, depending on your computer."
read -p "Build now? [y/N] " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]; then
	echo "Here we go, go make a cup of coffee (or bake a cake, maybe we're done by then...)"
	echo
	ninja -C out.gn/x64.release
	ninja -C out.gn/x64.debug
fi

echo
echo "Completed."
echo

