#ifndef BOX_HPP
#define BOX_HPP

#include <glm/vec3.hpp>


#include "Shape.hpp"
#include "color.hpp"

class Box : public Shape			//5.2
{
public:								//5.3
	Box();
	Box(glm::vec3 const& newmin_, glm::vec3 const& newmax_);
	Box(glm::vec3 const& newmin_, glm::vec3 const& newmax_, std::string const& newname_, Color const& newcolor_);

	~Box() override;				//5.8 (virtual)

	float area() const override;
	float volume() const override;

	std::ostream& print(std::ostream& os) const override;	//5.4

private:
	glm::vec3 min_;
	glm::vec3 max_;
};

#endif