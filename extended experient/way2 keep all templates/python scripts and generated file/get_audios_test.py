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
            Suffix_name=new_path.split('\\')[-1].split('.')[0]
            Suffix_name1=Suffix_name.split('_')[0][0]
            if Suffix_name1 =='O':
                Suffix_name1='10'
            elif Suffix_name1 =='Z':
                Suffix_name1='0'
            
            name=Suffix_name1+'_'+str(list[int(Suffix_name1)])+'.wav'
            name1=Suffix_name1+'_'+str(list[int(Suffix_name1)])+'.mfc'
            list[int(Suffix_name1)]=list[int(Suffix_name1)]+1
            dst_path=Target_area+'audiostest.txt'
            dst_path1=Target_area+'mfctest\\'+name1
            with open(dst_path,"a")as f:
                f.write(new_path)
                f.write('\t')
                f.write(dst_path1+'\n')
            
            
         
 
path='wav\\isolated_digits_ti_test_endpt'
Target_area=''
copy_file(path,Target_area)