################################################################################
# d.petrov 2020
# 
# Файл для автоматической сборки проекта.
# $(BASE_DIR) - корневая директория
# $(OUTPUT_FILENAME) - имя исполняемого файла
# $(SOURCE_PATH) - путь к директории с исходными файлами.
#		Из процесса компиляции будут автоматически исключены файлы,
#		в пути к которым присутствует слово windows.
# $(BUILD_DIR) - имя директории, где будет производиться сборка проекта.
#
################################################################################

BASE_DIR := ../..
OUTPUT_FILENAME := $(BASE_DIR)/com_sniffer.exe
SOURCE_PATH := $(BASE_DIR)/src
BUILD_DIR := build


# Команда поиска файлов (из папки msys)
FIND := /bin/find

# Создать список путей к директориям
DIR_LIST := $(shell $(FIND) $(SOURCE_PATH))

# Список *.cpp файлов
SRC_CPP_FILES := $(wildcard $(addsuffix /*.cpp,$(DIR_LIST)))
SRC_CPP_TEMPLATE := $(SRC_CPP_FILES:.cpp=._extension_)

# Флаги для компляции проекта
CCFLAGS += -O3
CCFLAGS += -Wall

# Полные имена компиляторов
CXX:= "g++"
LK := "g++"

# Список исходных файлов в директории $(BUILD_DIR)
src_o_files := $(SRC_CPP_FILES:.cpp=.obj) $(SRC_C_FILES:.c=.obj)

# Список объектных файлов в директории $(BUILD_DIR)
object_files := $(addprefix $(BUILD_DIR)/, $(notdir $(src_o_files)))

# Конвертирование строк с ошибками в формат visual studio ( ":XX:YY:" -> "(XX,YY)" )
GCC_TO_VS_MSG_CONVERT := 2>&1 | sed -e 's/:\([0-9]\+\):\([0-9]\+\)/(\1,\2)/g'

################################################################################
.PHONY: build update_ver build_makedir build_message clean

build: build_message $(OUTPUT_FILENAME)

$(OUTPUT_FILENAME): build_makedir $(SRC_CPP_TEMPLATE) #$(SRC_C_TEMPLATE)
	@	echo Linking...
	@	$(LK)   -o $@   $(object_files)  $(LKFLAGS)


$(SRC_CPP_TEMPLATE):
	@	echo $(notdir $(@:._extension_=.cpp))
	@	$(CXX)   $(CXXFLAGS)   -c $(@:._extension_=.cpp)   -o $(addprefix $(BUILD_DIR)/, $(notdir $(@:._extension_=.obj)))   $(GCC_TO_VS_MSG_CONVERT)

build_makedir:
	@	mkdir -p $(BUILD_DIR)

build_message:
	@	echo Compiling...

clean:
	@	echo Cleaning...
	@	rm -f $(OUTPUT_FILENAME)
	@	rm -f $(object_files)