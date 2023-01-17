#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <SFML\Graphics.hpp>

class renderer final {
	// not instanceable
	virtual ~renderer() = 0;
public:

	////////////////////////////////////////////////////////////
	/// \brief Clear the entire target with a single color
	///
	/// This function is usually called once every frame,
	/// to clear the previous contents of the target.
	///
	/// \param color Fill color to use to clear the render target
	///
	////////////////////////////////////////////////////////////
	static void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

	////////////////////////////////////////////////////////////
	/// \brief Change the current active view
	///
	/// The view is like a 2D camera, it controls which part of
	/// the 2D scene is visible, and how it is viewed in the
	/// render target.
	/// The new view will affect everything that is drawn, until
	/// another view is set.
	/// The render target keeps its own copy of the view object,
	/// so it is not necessary to keep the original one alive
	/// after calling this function.
	/// To restore the original view of the target, you can pass
	/// the result of getDefaultView() to this function.
	///
	/// \param view New view to use
	///
	/// \see getView, getDefaultView
	///
	////////////////////////////////////////////////////////////
	static void set_view(const sf::View& view);

	////////////////////////////////////////////////////////////
	/// \brief Get the view currently in use in the render target
	///
	/// \return The view object that is currently used
	///
	/// \see setView, getDefaultView
	///
	////////////////////////////////////////////////////////////
	static const sf::View& get_view();

	////////////////////////////////////////////////////////////
	/// \brief Get the default view of the render target
	///
	/// The default view has the initial size of the render target,
	/// and never changes after the target has been created.
	///
	/// \return The default view of the render target
	///
	/// \see setView, getView
	///
	////////////////////////////////////////////////////////////
	static const sf::View& get_default_view();

	////////////////////////////////////////////////////////////
	/// \brief Get the viewport of a view, applied to this render target
	///
	/// The viewport is defined in the view as a ratio, this function
	/// simply applies this ratio to the current dimensions of the
	/// render target to calculate the pixels rectangle that the viewport
	/// actually covers in the target.
	///
	/// \param view The view for which we want to compute the viewport
	///
	/// \return Viewport rectangle, expressed in pixels
	///
	////////////////////////////////////////////////////////////
	static sf::IntRect get_viewport(const sf::View& view);

	////////////////////////////////////////////////////////////
	/// \brief Convert a point from target coordinates to world
	///        coordinates, using the current view
	///
	/// This function is an overload of the mapPixelToCoords
	/// function that implicitly uses the current view.
	/// It is equivalent to:
	/// \code
	/// target.mapPixelToCoords(point, target.getView());
	/// \endcode
	///
	/// \param point Pixel to convert
	///
	/// \return The converted point, in "world" coordinates
	///
	/// \see mapCoordsToPixel
	///
	////////////////////////////////////////////////////////////
	static sf::Vector2f map_pixel_to_coords(const sf::Vector2i& point);

	////////////////////////////////////////////////////////////
	/// \brief Convert a point from target coordinates to world coordinates
	///
	/// This function finds the 2D position that matches the
	/// given pixel of the render target. In other words, it does
	/// the inverse of what the graphics card does, to find the
	/// initial position of a rendered pixel.
	///
	/// Initially, both coordinate systems (world units and target pixels)
	/// match perfectly. But if you define a custom view or resize your
	/// render target, this assertion is not true anymore, i.e. a point
	/// located at (10, 50) in your render target may map to the point
	/// (150, 75) in your 2D world -- if the view is translated by (140, 25).
	///
	/// For render-windows, this function is typically used to find
	/// which point (or object) is located below the mouse cursor.
	///
	/// This version uses a custom view for calculations, see the other
	/// overload of the function if you want to use the current view of the
	/// render target.
	///
	/// \param point Pixel to convert
	/// \param view The view to use for converting the point
	///
	/// \return The converted point, in "world" units
	///
	/// \see mapCoordsToPixel
	///
	////////////////////////////////////////////////////////////
	static sf::Vector2f map_pixel_to_coords(const sf::Vector2i& point, const sf::View& view);

	////////////////////////////////////////////////////////////
	/// \brief Convert a point from world coordinates to target
	///        coordinates, using the current view
	///
	/// This function is an overload of the mapCoordsToPixel
	/// function that implicitly uses the current view.
	/// It is equivalent to:
	/// \code
	/// target.mapCoordsToPixel(point, target.getView());
	/// \endcode
	///
	/// \param point Point to convert
	///
	/// \return The converted point, in target coordinates (pixels)
	///
	/// \see mapPixelToCoords
	///
	////////////////////////////////////////////////////////////
	static sf::Vector2i map_coords_to_pixel(const sf::Vector2f& point) ;

	////////////////////////////////////////////////////////////
	/// \brief Convert a point from world coordinates to target coordinates
	///
	/// This function finds the pixel of the render target that matches
	/// the given 2D point. In other words, it goes through the same process
	/// as the graphics card, to compute the final position of a rendered point.
	///
	/// Initially, both coordinate systems (world units and target pixels)
	/// match perfectly. But if you define a custom view or resize your
	/// render target, this assertion is not true anymore, i.e. a point
	/// located at (150, 75) in your 2D world may map to the pixel
	/// (10, 50) of your render target -- if the view is translated by (140, 25).
	///
	/// This version uses a custom view for calculations, see the other
	/// overload of the function if you want to use the current view of the
	/// render target.
	///
	/// \param point Point to convert
	/// \param view The view to use for converting the point
	///
	/// \return The converted point, in target coordinates (pixels)
	///
	/// \see mapPixelToCoords
	///
	////////////////////////////////////////////////////////////
	static sf::Vector2i map_coords_to_pixel(const sf::Vector2f& point, const sf::View& view) ;

	////////////////////////////////////////////////////////////
	/// \brief Draw a drawable object to the render target
	///
	/// \param drawable Object to draw
	/// \param states   Render states to use for drawing
	///
	////////////////////////////////////////////////////////////
	static void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

	////////////////////////////////////////////////////////////
	/// \brief Draw primitives defined by an array of vertices
	///
	/// \param vertices    Pointer to the vertices
	/// \param vertexCount Number of vertices in the array
	/// \param type        Type of primitives to draw
	/// \param states      Render states to use for drawing
	///
	////////////////////////////////////////////////////////////
	static void draw(const sf::Vertex* vertices, std::size_t vertexCount,
			  sf::PrimitiveType type, const sf::RenderStates& states = sf::RenderStates::Default);

	////////////////////////////////////////////////////////////
	/// \brief Draw primitives defined by a vertex buffer
	///
	/// \param vertexBuffer Vertex buffer
	/// \param states       Render states to use for drawing
	///
	////////////////////////////////////////////////////////////
	static void draw(const sf::VertexBuffer& vertexBuffer, const sf::RenderStates& states = sf::RenderStates::Default);

	////////////////////////////////////////////////////////////
	/// \brief Draw primitives defined by a vertex buffer
	///
	/// \param vertexBuffer Vertex buffer
	/// \param firstVertex  Index of the first vertex to render
	/// \param vertexCount  Number of vertices to render
	/// \param states       Render states to use for drawing
	///
	////////////////////////////////////////////////////////////
	static void draw(const sf::VertexBuffer& vertexBuffer, std::size_t firstVertex, 
			  std::size_t vertexCount, const sf::RenderStates& states = sf::RenderStates::Default);

	////////////////////////////////////////////////////////////
	/// \brief Return the size of the rendering region of the target
	///
	/// \return Size in pixels
	///
	////////////////////////////////////////////////////////////
	static sf::Vector2u get_size();

	////////////////////////////////////////////////////////////
	/// \brief Save the current OpenGL render states and matrices
	///
	/// This function can be used when you mix SFML drawing
	/// and direct OpenGL rendering. Combined with popGLStates,
	/// it ensures that:
	/// \li SFML's internal states are not messed up by your OpenGL code
	/// \li your OpenGL states are not modified by a call to a SFML function
	///
	/// More specifically, it must be used around code that
	/// calls Draw functions. Example:
	/// \code
	/// // OpenGL code here...
	/// window.pushGLStates();
	/// window.draw(...);
	/// window.draw(...);
	/// window.popGLStates();
	/// // OpenGL code here...
	/// \endcode
	///
	/// Note that this function is quite expensive: it saves all the
	/// possible OpenGL states and matrices, even the ones you
	/// don't care about. Therefore it should be used wisely.
	/// It is provided for convenience, but the best results will
	/// be achieved if you handle OpenGL states yourself (because
	/// you know which states have really changed, and need to be
	/// saved and restored). Take a look at the resetGLStates
	/// function if you do so.
	///
	/// \see popGLStates
	///
	////////////////////////////////////////////////////////////
	static void push_gl_states();

	////////////////////////////////////////////////////////////
	/// \brief Restore the previously saved OpenGL render states and matrices
	///
	/// See the description of pushGLStates to get a detailed
	/// description of these functions.
	///
	/// \see pushGLStates
	///
	////////////////////////////////////////////////////////////
	static void pop_gl_states();

	////////////////////////////////////////////////////////////
	/// \brief Reset the internal OpenGL states so that the target is ready for drawing
	///
	/// This function can be used when you mix SFML drawing
	/// and direct OpenGL rendering, if you choose not to use
	/// pushGLStates/popGLStates. It makes sure that all OpenGL
	/// states needed by SFML are set, so that subsequent draw()
	/// calls will work as expected.
	///
	/// Example:
	/// \code
	/// // OpenGL code here...
	/// glPushAttrib(...);
	/// window.resetGLStates();
	/// window.draw(...);
	/// window.draw(...);
	/// glPopAttrib(...);
	/// // OpenGL code here...
	/// \endcode
	///
	////////////////////////////////////////////////////////////
	static void reset_gl_states();

private:
	static inline sf::RenderTarget* s_target = nullptr;
public:
	static void __set_target(sf::RenderTarget* target);
};

#endif // !RENDERER_HPP