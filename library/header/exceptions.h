#include <exception>

namespace ZNN {
	class NUMBERINPUTMISMATCH : public std::exception {
		const char* what() const throw() {
			return ("Number of Inputs to Neural Network not matching Input neurons!");
		}
	};
	class LEARNRATEZERO : public std::exception {
		const char* what() const throw() {
			return ("Learn-Rate set to zero, Neural Network can't operate in such a condition");
		}
	};
	class LAYERSIZEZERO : public std::exception {
		const char* what () const throw () {
			return ("Layer-Size is zero.");
		}
	};
}