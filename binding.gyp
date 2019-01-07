{
  # NOTE: 'module_name' and 'module_path' come from the 'binary' property in package.json
  # node-pre-gyp handles passing them down to node-gyp when you build from source
  "targets": [
    {
      # node-pre-gyp doesn't support cmake-js, this is workaround to run cmake from gyp
      "target_name": "<(module_name)",
      "product_dir": "<(module_path)",
      "type": "none",
      "actions": [
        {
          # run npm cmake-rebuild
          "action_name": "ncmake",
          "inputs": [""],
          "outputs": [""],
          "action": ["npm", "run", "cmake-rebuild", "-DNAPI_VERSION=<(napi_build_version)"]
        }
      ]
    },
    # arrange compiled files for node-pre-gyp
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [ "<(module_name)" ],
      "copies": [
        {  
          "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
          "destination": "<(module_path)"
        },
        {
          # include libtorch shared libraries
          "files": [
            "libtorch/lib/libtorch.so", "libtorch/lib/libtorch.so.1", "libtorch/lib/libc10.so",
            "libtorch/lib/libcaffe2.so", "libtorch/lib/libmkldnn.so.0",
            "libtorch/lib/libmkldnn.so.0.14.0", "libtorch/lib/libonnxifi_dummy.so",
            "libtorch/lib/libgomp-7bcb08ae.so.1"
          ],
          "destination": "<(module_path)"
        }
      ]
    }
  ]
}

