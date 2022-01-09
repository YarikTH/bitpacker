##########################################################################
# configuration
##########################################################################

##########################################################################
# documentation of the Makefile's targets
##########################################################################

# main target
all:
	@echo "This Makefile is for the maintenance of the repository, not for building."
	@echo "Supported targets:"
	@echo "* pretty_check - check if all cmake and c++ files are properly formatted"
	@echo "* pretty - prettify all cmake and c++ files"

##########################################################################
# Prettify
##########################################################################

# check if all cmake and c++ files are properly formatted
pretty_check:
	@./support/thirdparty/pretty.py/pretty.py --clang-format clang-format-11 --exclude="tests/thirdparty" --exclude="support/thirdparty" --check -

# prettify all cmake and c++ files
pretty:
	@./support/thirdparty/pretty.py/pretty.py --clang-format clang-format-11 --exclude="tests/thirdparty" --exclude="support/thirdparty" -
