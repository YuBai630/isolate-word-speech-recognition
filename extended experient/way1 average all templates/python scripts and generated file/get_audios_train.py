import os
import shutil

def copy_file(path,Target_area):#传入需要遍历的根目录和需要复制到的区域
    path_list=os.listdir(path)
    for new_path in path_list:
        new_path=os.path.join(path,new_path)
        if os.path.isdir(new_path):
            copy_file(new_path,Target_area)
        elif os.path.isfile(new_path):
            Suffix_name=new_path.split('\\')[-1].split('.')[0]
            name1=Suffix_name+'.mfc'
            dst_path=Target_area+'audios_train.txt'
            dst_path1=Target_area+'mfctrain\\'+name1
            with open(dst_path,"a")as f:
                f.write(path+'\\'+new_path.split('\\')[-1])
                f.write('\t')
                f.write(dst_path1+'\n')
            
         
 
path='new'
Target_area=''
copy_file(path,Target_area)