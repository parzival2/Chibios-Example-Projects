import subprocess
import os

class DepFolderParser(object):
    def __init__(self):
        """
        Runs make first which will create a dep folder. The dep folder contains all the files that were
        required to build the program. It contains lists of header files and source files divided that were
        utilized in compiling the specific program. This file will parse each and every one of those file and
        extract include folders along with the files that were compiled.
        """
        # The first thing that we need to do after launching this file is to run make in the folder.
        # Get the working directory to launch the make at the specific folder
        self.__projectFolder = os.path.dirname(os.path.abspath(__file__))
        self.__projectName = self.__projectFolder.split("/")[-1]
        calledProcess = subprocess.Popen(["make", "-j", "4&"],
                                       universal_newlines=True,
                                         cwd=self.__projectFolder,
                                         shell=True)
        # Wait for the building process to finish.
        calledProcess.wait()

        # Create some variables to store all the files
        # A List to store all the source files. These are the files that end with '.c'
        self.__sourceFileList = []
        # A List of files that are already in the folder
        self.__fileListInFolder = []
        # A List of include folders
        self.__includeFolderList = []
        self.__allIncludeFileList = []
        # Parse the .inludes file whether the user has added any includes
        self.__parseIncludesFile()
        # Search for files in the project folder.
        self.__addFilesInCurrentFolder()
        # After that we can begin parsing the dep folder.
        self.__parseDepFolder()
        # Then we have to fill the files .files and .includes
        self.__fillDotFiles()
        # Then fill up the include folder file
        self.__fillIncludeFiles()
        # Finally, we also have to update the config file using the halconf.h
        self.__updateConfigFile()

    def __parseIncludesFile(self):
        """
        Parse include for user includes
        Returns
        -------

        """

        includesFile = self.__projectName + '.includes'
        includesFilePath = os.path.join(self.__projectFolder, includesFile)
        index = 0
        if(os.path.exists(includesFilePath)):
            with open(includesFilePath, 'r') as fileObj:
                linesList = fileObj.readlines()
                for line in linesList:
                    if("===" in line):
                        break
                    self.__includeFolderList.append(line)
                    print(line)
                    index += 1
        self.__includeFolderList.insert(index, "===")
        print(self.__includeFolderList)

    def __addFilesInCurrentFolder(self):
        """
        Add the files in the current project folder.
        """
        for root, dir, files in os.walk(self.__projectFolder):
            for file in files:
                if(file.endswith('.c') or file.endswith('.cpp')):
                    filePath = os.path.join(root, file)
                    fileRelPath = os.path.relpath(filePath)
                    self.__sourceFileList.append(fileRelPath)
                elif(file.endswith('.h') or file.endswith('.hpp')):
                    filePath = os.path.join(root, file)
                    fileRelPath = os.path.relpath(filePath)
                    self.__allIncludeFileList.append(filePath)

    def __parseDepFolder(self):
        """
        Checks if the Dep folder is available and will begin parsing the files inside it.
        Returns
        -------

        """
        depFolder = os.path.join(self.__projectFolder, "dep")

        depFolderExists = os.path.exists(depFolder)
        if(depFolderExists):
            filesList = os.listdir(depFolder)
            for file in filesList:
                filePath = os.path.join(depFolder, file)
                with open(filePath, 'r') as fileObj:
                    linesList = fileObj.readlines()
                    for line in linesList:
                        # Ignore the lines that end with ":" or if the lines are just empty.
                        if(":" in line or line == "\n"):
                            pass
                        else:
                            # Split the line at "\"
                            splittedLines = line.split('\\')
                            strippedPaths = splittedLines[0].strip()
                            # Start extracting source files
                            if(strippedPaths.endswith(".c") or strippedPaths.endswith(".cpp")):
                                self.__sourceFileList.append(strippedPaths)
                            # The files that end with '.h' extenison are the include files.
                            elif(strippedPaths.endswith(".h") or strippedPaths.endswith(".hpp")):
                                if("/" not in strippedPaths):
                                    # Divide them since sometimes they have multiple files on the same line
                                    includeFileList = strippedPaths.split(" ")
                                    if(len(includeFileList) > 1):
                                        for includeFile in includeFileList:
                                            if(includeFile not in self.__fileListInFolder):
                                                self.__fileListInFolder.append(includeFile)
                                    else:
                                        if(strippedPaths not in self.__fileListInFolder):
                                            self.__fileListInFolder.append(strippedPaths)
                                else:
                                    self.__allIncludeFileList.append(strippedPaths)
        self.__finalizeIncludeFolders(self.__allIncludeFileList)

    def __finalizeIncludeFolders(self,
                                 includeFileList):
        """
        We will get a list of all the include files. We need to extract include folders from them without
        repeating.
        Returns
        -------

        """
        self.__allIncludeFileList = includeFileList
        for includeFile in includeFileList:
            includeFile = includeFile.strip()
            # Split the file path using "/"
            splitWords = includeFile.split("/")
            # Form a path without using the first and the last word
            wordsForPath = splitWords[1:-1]
            joinedPath = "/".join(wordsForPath)
            joinedPath = "/" + joinedPath + "/"
            if(joinedPath not in self.__includeFolderList):
                self.__includeFolderList.append(joinedPath)

    def __fillDotFiles(self):
        """
        Fills the .files file with the list of source file
        Returns
        -------

        """
        filePath = os.path.join(self.__projectFolder,
                                self.__projectName+".files")
        with open(filePath, 'w+') as fileObj:
            for line in self.__sourceFileList:
                fileObj.write(line + "\n")
            # All the add the .h files that are in the folder
            for line in self.__fileListInFolder:
                fileObj.write(line + "\n")
            # All the include files as well
            for line in self.__allIncludeFileList:
                fileObj.write(line + "\n")
        fileObj.close()

    def __fillIncludeFiles(self):
        """
        Fill the .includes file with list of all the include files and folders collected.
        Returns
        -------

        """
        filePath = os.path.join(self.__projectFolder,
                                self.__projectName+".includes")
        with open(filePath, "w+") as fileObj:
            for line in self.__includeFolderList:
                fileObj.write(line.strip() + "\n")
        fileObj.close()

    def __updateConfigFile(self):
        """
        Update the config file using the values from halconf.h
        Returns
        -------

        """
        filePath = os.path.join(self.__projectFolder,
                                self.__projectName+".config")
        configLinesList = []
        # Read the halconf.h file
        with open("halconf.h", 'r') as fileObj:
            linesList = fileObj.readlines()
            for line in linesList:
                # Only consider lines that contain #define and TRUE or False
                if("#define " in line and("TRUE" in line or "FALSE" in line)):
                    splittedLine = line.strip().split(" ")
                    if("TRUE" in line):
                        trueLine = splittedLine[0] + " " + splittedLine[1] + " 1\n"
                        configLinesList.append(trueLine)
                    elif("FALSE" in line):
                        falseLine = splittedLine[0] + " " + splittedLine[1] + " 0\n"
                        configLinesList.append(falseLine)
        fileObj.close()
        # Now write the config file
        with open(filePath, 'w+') as writableFileObj:
            for line in configLinesList:
                writableFileObj.write(line)
        writableFileObj.close()

if __name__ == '__main__':
    dep = DepFolderParser()