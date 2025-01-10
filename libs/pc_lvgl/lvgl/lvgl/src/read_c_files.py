
from os import listdir
from os.path import isfile, join

folder_list = [
    'lv_core',
    'lv_draw',
    'lv_font',
    'lv_gpu',
    'lv_hal',
    'lv_misc',
    'lv_themes',
    'lv_widgets'
]

for f in folder_list:
    path = '${}/lvgl/src/{}/'.format('{CMAKE_CURRENT_SOURCE_DIR}',f)
    for i in listdir(f):
        if i.find('.c') > 0:
            print(f'"{path}{i}"')