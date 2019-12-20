import os
import shutil
list=[0]*11

def copy_file(path,Target_area):#传入需要遍历的根目录和需要复制到的区域
    path_list=os.listdir(path)
    for new_path in path_list:
        new_path=os.path.join(path,new_path)
        if os.path.isdir(new_path):
            copy_file(new_path,Target_area)
        elif os.path.isfile(new_path):
            dst_path=Target_area+'train_filelist.txt'
            with open(dst_path,"a")as f:
                f.write(new_path+'\n')
            
         
 
path='mfctrain'
Target_area=''
copy_file(path,Target_area)