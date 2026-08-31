#!/usr/bin/env python3
import os
import json
import glob

def generate_matrix():
    targets = []
    # 扫描路径：键盘定义在 keyboards/xtips/ 下
    kb_paths = glob.glob('keyboards/xtips/*/*')
    
    print(f"发现路径: {kb_paths}", file=os.sys.stderr)  # 调试输出
    
    for path in kb_paths:
        parts = path.split('/')
        if len(parts) < 4:
            continue
            
        kb = parts[2]      # 例如 p25s
        version = parts[3] # 例如 v2
        
        # 检查键映射是否存在
        vial_path = os.path.join(path, 'keymaps', 'vial')
        default_path = os.path.join(path, 'keymaps', 'default')
        
        keymap = None
        if os.path.exists(vial_path) and os.path.isdir(vial_path):
            keymap = 'vial'
        elif os.path.exists(default_path) and os.path.isdir(default_path):
            keymap = 'default'
        else:
            print(f"⚠️ 警告: {kb}/{version} 没有找到 vial 或 default 键映射，跳过", file=os.sys.stderr)
            continue
            
        targets.append({
            'kb': kb,
            'version': version,
            'keymap': keymap
        })
    
    print(f"生成任务: {targets}", file=os.sys.stderr)  # 调试输出
    
    # 输出JSON数组供GitHub Actions使用
    print(json.dumps(targets))

if __name__ == '__main__':
    generate_matrix()