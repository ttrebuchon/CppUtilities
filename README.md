# CppUtilities

A collection of various tools, side projects, and challenges I've written (and am writing) for learning purposes, primarily on my phone. Many of the projects,  while functional, aren't in finished states and could use a lot of cleaning up. Some are alsp in non-functional states as well.

This is NOT intended to be professional-level code, and the modules within this repo are primarily useful as proof-of-concepts and code snippets. Additionally, after beginning some of the modules I discovered that some of those exact same ideas were already present in Boost, with full functionality and more polish.

The files under the /Deps folder are open source libraries that I use in one or more of my modules, and although I have modified some of them (For example, modified Castor to fix unused-typedef warnings by replacing them with static assertions), they are NOT my code and each have their own licensing that they are distributed under.



The code is primarily written and debugged in the C4Droid Android application, and committed with the mGit Android app. Because of this, there are some out of the ordinary workarounds in the build process and with dependencies that could be solved by using a desktop build system.
