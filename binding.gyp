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
          "conditions": [
            [ "OS=='linux'",
                {"action": ["npm", "run", "cmake-rebuild", "-DNAPI_VERSION=<(napi_build_version)"]}
            ],
            [ "OS=='win'",
                {"action": ["npm run cmake-rebuild", "-DNAPI_VERSION=<(napi_build_version)"]}
            ]
          ]
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
          "files": [ ],
          "conditions": [
            [ "OS=='linux'",
                { "files+": [
                    "libtorch/lib/libc10.so",
                    "libtorch/lib/libcaffe2_detectron_ops.so",
                    "libtorch/lib/libcaffe2_module_test_dynamic.so",
                    "libtorch/lib/libfbjni.so",
                    "libtorch/lib/libgomp-753e6e92.so.1",
                    "libtorch/lib/libpytorch_jni.so",
                    "libtorch/lib/libtorch.so"
                  ]
                }
            ],
            [ "OS=='win'",
                { "files+": ["libtorch/lib/c10.dll",
                       "libtorch/lib/caffe2.dll",
                       "libtorch/lib/libiompstubs5md.dll",
                       "libtorch/lib/caffe2_module_test_dynamic.dll",
                       "libtorch/lib/libiomp5md.dll",
                       "libtorch/lib/onnxifi_dummy.dll",
                       "libtorch/lib/onnxifi.dll",
                       "libtorch/lib/torch.dll"]
                }
            ]
          ],
          "destination": "<(module_path)"
        }
      ]
    }
  ]
}