#pragma once

#include "TextImage.h"
#include <pango/pangocairo.h>

namespace dawn
{
    class PangoCairoTextImage : public TextImage
    {
    public:
        PangoCairoTextImage(std::string text, TextStyle *style) : TextImage(text, style) {
            cairo_surface_t *temp_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 0, 0);
            m_cairoContext = cairo_create (temp_surface);
            cairo_surface_destroy (temp_surface);

            m_pangoLayout = pango_cairo_create_layout(m_cairoContext);
        }

        virtual ~PangoCairoTextImage() {
            g_object_unref (m_pangoLayout);
            cairo_destroy (m_cairoContext);
        }

        virtual BufferPtr buffer() {
            std::cout << "Rendering text " << m_text << std::endl;

            int width;
            int height;
            setupContext(&width, &height);
            int stride = width * 4;

            size_t raw_length = stride * height;
            uint8_t *raw = new uint8_t[raw_length]();
            uint8_t *flippedRaw = new uint8_t[raw_length];

            cairo_surface_t *surface = cairo_image_surface_create_for_data((unsigned char *)raw,
                                                         CAIRO_FORMAT_ARGB32,
                                                         width,
                                                         height,
                                                         stride);
            cairo_t *render_context = cairo_create(surface);

            vec4f foreground = m_style->foreground();
            cairo_set_source_rgba (render_context, foreground[0], foreground[1], foreground[2], foreground[3]); // TODO Move to setup?
            pango_cairo_show_layout (render_context, m_pangoLayout);

            cairo_surface_destroy(surface);
            cairo_destroy (render_context);

            for (unsigned i = 0; i < height; ++i) {
                const uint8_t *srcBeg = raw + (stride * (height - i - 1));
                const uint8_t *srcEnd = srcBeg + stride;

                std::copy(srcBeg, srcEnd, flippedRaw + stride * i);
            }

            BufferPtr buffer = BufferPtr(new Buffer(flippedRaw, raw_length));

            delete [] raw;
            delete [] flippedRaw;

            return buffer;
        }

        virtual unsigned int width() {
            int width;
            int height;
            setupContext(&width, &height);

            return width;
        }

        virtual unsigned int height() {
            int width;
            int height;
            setupContext(&width, &height);

            return height;
        }

        virtual CONSTANTS::PixelFormat format() { return CONSTANTS::BGRAFormat; }

    private:
        void setupContext(int *w, int *h) {
            //pango_layout_set_text (layout, text, -1);
            pango_layout_set_markup(m_pangoLayout, m_text.c_str(), -1);

            /* Load the font */
            PangoFontDescription *desc = pango_font_description_from_string (m_style->font().c_str());
            pango_layout_set_font_description (m_pangoLayout, desc);
            pango_font_description_free (desc);

            int layout_width = m_style->maxWidth();
            int layout_height = m_style->maxHeight();

            if (layout_width > 0) {
                pango_layout_set_width(m_pangoLayout, layout_width * PANGO_SCALE);
            }

            if (layout_height > 0) {
                pango_layout_set_height(m_pangoLayout, layout_height * PANGO_SCALE);
            }

            switch (m_style->align()) {
                case CONSTANTS::TextAlign::Left:
                    pango_layout_set_alignment (m_pangoLayout, PANGO_ALIGN_LEFT);
                    break;

                case CONSTANTS::TextAlign::Right:
                    pango_layout_set_alignment (m_pangoLayout, PANGO_ALIGN_RIGHT);
                    break;

                case CONSTANTS::TextAlign::Center:
                    pango_layout_set_alignment (m_pangoLayout, PANGO_ALIGN_CENTER);
                    break;
            }

            int content_width = 0;
            int content_height = 0;
            pango_layout_get_pixel_size(m_pangoLayout, &content_width, &content_height);

            if (layout_width < 0) {
                layout_width = content_width;
            }

            if (layout_height < 0) {
                layout_height = content_height;
            }

            *w = layout_width;
            *h = layout_height;
        }

        cairo_t *m_cairoContext;
        PangoLayout *m_pangoLayout;
    };
}
