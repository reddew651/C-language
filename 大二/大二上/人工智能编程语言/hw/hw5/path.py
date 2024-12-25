import os

class FileInfo:
    def __init__(self, name, size, file_type):
        self.name = name
        self.size = size
        self.file_type = file_type

class FolderInfo:
    def __init__(self, name):
        self.name = name
        self.files = []
        self.subfolders = []

def analyze_directory(path):
    if not os.path.isdir(path):
        print(f"路径 '{path}' 不是一个有效目录。")
        return

    def analyze_folder(current_path):
        folder_info = FolderInfo(os.path.basename(current_path))
        
        for item in os.listdir(current_path):
            item_path = os.path.join(current_path, item)
            
            if os.path.isfile(item_path):
                file_size = os.path.getsize(item_path) // 1024  # 以KB为单位
                file_type = os.path.splitext(item)[1].lstrip('.')
                folder_info.files.append(FileInfo(name=item, size=file_size, file_type=file_type))
            elif os.path.isdir(item_path):
                folder_info.subfolders.append(analyze_folder(item_path))
        
        return folder_info

    def print_folder_info(folder_info, indent=""):
        print(f"{indent} | -- {folder_info.name} [{len(folder_info.files)} files]")

        for file in folder_info.files:
            print(f"{indent} | -- {file.name} ({file.size}KB) - {file.file_type}")

        for subfolder in folder_info.subfolders:
            print_folder_info(subfolder, indent + " |  ")

    root_folder_info = analyze_folder(path)
    print_folder_info(root_folder_info)

# 示例用法
directory_path = input("请输入目录路径：")
analyze_directory(directory_path)