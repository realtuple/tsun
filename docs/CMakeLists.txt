set(DOXYGEN_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/docs/")
set(TSUN_DOCS_SOURCES
  "${PROJECT_SOURCE_DIR}/tsunc/include"
)

doxygen_add_docs(
  tsun-docs
  ${TSUN_DOCS_SOURCES}
)
