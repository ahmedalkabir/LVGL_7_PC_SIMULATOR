
from os import listdir
from os.path import isfile, join

folder_list = [
    'display',
    'indev',
]

for f in folder_list:
    path = '${}/{}/'.format('{CMAKE_CURRENT_SOURCE_DIR}',f)
    for i in listdir(f):
        if i.find('.c') > 0:
            print(f'"{path}{i}"')